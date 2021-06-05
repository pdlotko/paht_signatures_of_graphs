#include "signatures_of_graphs.h"

int main()
{
	/*
	//	1-----2
	//	|   /  \
	//	| /     \
	//	3--------4-----0
	std::vector< std::vector<unsigned short int> > incidence_list(5);
	std::vector<unsigned short int> neighs_0 = {4};
	std::vector<unsigned short int> neighs_1 = {2,3};
	std::vector<unsigned short int> neighs_2 = {1,3,4};
	std::vector<unsigned short int> neighs_3 = {1,2,4};
	std::vector<unsigned short int> neighs_4 = {0,2,3};
	incidence_list[0] = neighs_0;
	incidence_list[1] = neighs_1;
	incidence_list[2] = neighs_2;
	incidence_list[3] = neighs_3;
	incidence_list[4] = neighs_4;	
	std::vector< std::vector<unsigned short int> > all_paths = compute_signatures_of_graph( 5 , incidence_list );
	*/
	std::pair< unsigned short int , std::vector< std::vector<unsigned short int> > > graph = read_graph_from_file( "graph2" ); 
	/*
	cerr << "The graph having : " << graph.first << " vertices and the following edges: \n";
	for ( size_t i = 0 ; i != graph.second.size() ; ++i )
	{
		cerr << "From : " << i << " to ";
		for ( size_t j = 0 ; j != graph.second[i].size() ; ++j )cout << graph.second[i][j] << " ";
		cout << endl;
	}
	*/
	
	unsigned cap_on_path_length = 30;
	std::vector< std::vector<unsigned short int> > all_paths = compute_paths_in_graph( graph.first , graph.second , cap_on_path_length );
	
	std::vector< unsigned > path_signature = compute_path_signatures( all_paths );

/*
	cerr << "Here are the paths: \n";
	for ( size_t i = 0 ; i != all_paths.size() ; ++i )
	{
		for ( size_t j = 0 ; j != all_paths[i].size() ; ++j )
		{
			cerr << all_paths[i][j] << " ";
		}
		cerr << endl;
	}	
*/
	
	/*
	cerr << "Here are path signatures : \n";
	for ( size_t i = 0 ; i != path_signature.size() ; ++i )
	{
		cerr << path_signature[i] << " ";
	}
	*/
	
	
	std::vector< std::vector< std::vector< unsigned short int > > > gr_paths = compute_graded_paths( all_paths );
	/*
	cerr << "Here are the graded paths : \n";
	for ( size_t i = 0 ; i != gr_paths.size() ; ++i )
	{
		cerr << "Gradation level : " << i << endl;
		for ( size_t j = 0 ; j != gr_paths[i].size() ; ++j )
		{
			for ( size_t k = 0 ; k != gr_paths[i][j].size() ; ++k )
			{
				cout << gr_paths[i][j][k] << " ";
			}
			cout << endl;
		}
	}
	*/ 
	
	
	//Now we will build a poset:
	std::vector< std::vector< poset_element_incidence > > poset = create_poset( gr_paths );
	
	
	cerr << "Here is the poset: \n";
	for ( size_t lev = 1 ; lev != poset.size() ; ++lev )
	{
		cout << endl << endl << "Level : " << lev << endl;
		for ( size_t i = 0 ; i != poset[lev].size() ; ++i )
		{
			cout << "\n Boundary of a path : ";
			for ( size_t aa = 0 ; aa != gr_paths[lev][i].size() ; ++aa )cout << gr_paths[lev][i][aa] << " ";
			cout <<  " is : ";
			for ( size_t aa = 0 ; aa != poset[lev][i].down.size() ; ++aa )
			{
				for( size_t bb = 0 ; bb != gr_paths[lev-1][ poset[lev][i].down[aa].first ].size() ; ++bb )cout << gr_paths[lev-1][ poset[lev][i].down[aa].first ][bb] << " ";
				cout << " with a number of path : " << poset[lev][i].down[aa].second << endl;
			}
			//getchar();
		}
	}
	getchar();
	
	
	std::vector< std::vector<size_t> > ms = maximal_simplices_in_poset( poset );
/*	
	cerr << "Here are the maximal pahts : \n";
	for ( size_t i = 0 ; i != ms.size() ; ++i )
	{
		for ( size_t j = 0 ; j != ms[i].size() ; ++j )cout << ms[i][j] << " ";
		cout << endl;
	}
	*/
	return 0;
}


