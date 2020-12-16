#include "lcs.h"

/**
 * A no branching version of the LCS algorithm.
 * Muxes out intermediate values wherever a 
 * branch might normally be.
 *
 * a: the first string for comparison
 * b: the second string for comparison
 * cache: the cache entries (size is (m+1)*(n+1))
 * m: length of string a
 * n: length of string b
 */
void lcs_no_branching(char* a, char* b, cache_entry* cache, size_t m, size_t n) 
{
	int i, j;

	//convert string size to table dims
	m = m + 1; 
	n = n + 1;

	// vars to buffer intermediate values for muxing
	int ul_cache_idx, u_cache_idx, l_cache_idx;
	int u, l, ul;
	int value_case_buf[3];
	int came_from_case_buf[3];

	int is_match;
	int case_idx;
	int cache_idx;

	for(i = 1; i < m; i++)
	{
		for(j = 1; j < n; j++)
		{
			// fill case buffer with pre-computed cases (no branching)
			l_cache_idx  = (i * m) + (j-1);
			u_cache_idx  = (i * (m-1)) + (j);
			ul_cache_idx = (i * (m-1)) + (j-1);

			l = cache[l_cache_idx].value;
			u = cache[u_cache_idx].value;
			ul = cache[ul_cache_idx].value;

			//store intermediate indexes and came_from indexes for later
			came_from_case_buf[0] = l_cache_idx;  // left
			came_from_case_buf[1] = u_cache_idx;  // upper
			came_from_case_buf[2] = ul_cache_idx; // upper-left

			value_case_buf[0] = l;      // left 
			value_case_buf[1] = u;      // upper
			value_case_buf[2] = ul + 1; // upper-left

			// mux out value from the cases
			// is_match -> case = 2
			// ~is_match && upper > left-> case = 1
			// ~is_match && upper <= left-> case = 0
			is_match = (a[i-1] == b[j-1]); //recall we shifted m & n up at the start
			case_idx  = (is_match << 1) | ((u > l) >> is_match);

			cache_idx = (i * m) + j;
			cache[cache_idx].value     = value_case_buf[case_idx];
			cache[cache_idx].came_from = came_from_case_buf[case_idx];
		}
	}
}
