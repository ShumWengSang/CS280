#include <random>
#include <algorithm>
#include <iterator> // stream iterator
#include <numeric>  // iota


#include "bst-map.h"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <string> 

void simple_inserts( CS280::BSTmap<int,int> & map, std::vector<int> const& data ) {
    //insert (using index operator) and perform sanity check each time
    for ( int const & key : data ) {
        map[ key ] = key*key; //value is not important
        // if you have the method below, uncomment next line
        // if (!map.sanityCheck()) std::cout << "Error\n";
    }
}

void test0() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data {1,2,3,4,5};
    simple_inserts( map, data );
    std::cout << map << std::endl;
}
void test1() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data  {5,4,3,2,1};
    simple_inserts( map, data );
    std::cout << map << std::endl;
}
void test2() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data {3,4,1,5,2};
    simple_inserts( map, data );
    std::cout << map << std::endl;
}
////////////////////////////////////////////////
// implement basics of the iterator
// and find

void simple_finds( CS280::BSTmap<int,int> & map, std::vector<int> const& data ) {
    //insert all and perform sanity check each time
    for ( int const & key : data ) {
        CS280::BSTmap<int,int>::iterator it = map.find( key );
        if ( it == map.end() ) {
            std::cout << "cannot find value " << key << std::endl;
        }
    }
}
void test3() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data {3,4,1,5,2};
    simple_inserts( map, data );
    simple_finds( map, data );
}
////////////////////////////////////////////////
// implement delete
void simple_deletes( CS280::BSTmap<int,int> & map, std::vector<int> const& data ) {
    //insert all and perform sanity check each time
    for ( int const & key : data ) {
        CS280::BSTmap<int,int>::iterator it = map.find( key );
        if ( it == map.end() ) {
            std::cout << "cannot find value " << key << std::endl;
        } else {
            map.erase( it );
            // if you have the method below, uncomment next line
            // if (!map.sanityCheck()) std::cout << "Error\n";
        }
    }

    //    std::cout << "--------------------\n" << map << std::endl;
}

void test4() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data {3,4,1,5,2};
    simple_inserts( map, data );
    std::cout << map << std::endl;
    simple_deletes( map, data ); // delete in the same order as insert
    std::cout << map << std::endl;
}

void test5() {
    CS280::BSTmap<int,int> map;
    std::vector<int> data {3,4,1,5,2};
    simple_inserts( map, data);
    std::cout << map << std::endl;
    std::vector<int> data_rev( data.rbegin(), data.rend() );
    simple_deletes( map, data_rev ); // delete in reverse order
    std::cout << map << std::endl;
}

////////////////////////////////////////////////
// a little more testing for inserts and deletes
// insert 1,...,100 in random order
// delete 1,...,100 in random order
// final map should be empty
// run test6 several times (10000 times?)
// try larger N
// check with Dr. Memory - better catch error now
void test6() {
    int N = 100;
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    simple_inserts( map, data);
    std::cout << map << std::endl;

    // reshuffle data
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
    simple_deletes( map, data ); // delete in reverse order
    std::cout << map << std::endl;
}

////////////////////////////////////////////////
// a little more testing for inserts and deletes
// now mix inserts and deletes
// test is randomized, so no output provided:
// check for crashes, check with valgrind
void inserts_delete_random( int N, int num_iter, 
        int min_number_to_insert, int max_number_to_insert, //min_number_to_insert < max_number_to_insert
        float ratio_to_delete, // 0..1
        bool perform_checks // false - speed only, true - mostly correctness
        ) {
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );   // data to insert (i.e. NOT in the map )
    std::iota( data.begin(), data.end(), 1 );
    std::vector<int> map_content; // initially empty 


    for ( int i=0; i<num_iter; ++i ) {
        // insert some number of elements
        std::random_device                      rd;
        std::mt19937                            gen( rd() );
        // number of elements to insert, min of 
        std::uniform_int_distribution<unsigned int>      dis( min_number_to_insert, max_number_to_insert );
        unsigned int num_insert = dis( gen );
        if ( num_insert > data.size() ) { num_insert = data.size(); }

//        std::cout << "insert " << num_insert << " elements\n";

        // insert from the back of shuffled data
        std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
//        std::copy( data.begin() + data.size() - num_insert, data.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";
        simple_inserts( map, std::vector<int>( data.begin() + data.size() - num_insert, data.end() ) );
        map_content.insert( map_content.end(), data.begin() + data.size() - num_insert, data.end() );
        data.resize( data.size() - num_insert );

        int num_delete = num_insert * ratio_to_delete;
//        std::cout << "delete " << num_delete << " elements\n";
        // delete some
        std::shuffle( map_content.begin(), map_content.end(), std::mt19937{std::random_device{}()} );
//        std::copy( map_content.begin() + map_content.size() - num_delete, map_content.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";
        simple_deletes( map, std::vector<int>( map_content.begin() + map_content.size() - num_delete, map_content.end() ) );
        data.insert( data.end(), map_content.begin() + map_content.size() - num_delete, map_content.end() );
        map_content.resize( map_content.size() - num_delete );

#if 0
        std::cout << "BSTmap size " << map.size() << "\n";
        std::cout << "---------------------------------------\n";
        std::cout << map << "\n";
        std::cout << "---------------------------------------\n";
#endif
        if ( perform_checks and map.size() != map_content.size() ) {
            std::cout << "Wrong size\n";
        }
    }

    if ( perform_checks ) {
        // check all data is in a tree
        for ( int const& el :  data ) {
            if ( map.find( el ) != map.end() ) {
                std::cout << "Error - found element that should not be in the tree\n";
            }
        }

        // check we can all data is in a tree
        for ( int const& el :  map_content ) {
            if ( map.find( el ) == map.end() ) {
                std::cout << "Error - not found\n";
            }
        }
    }
}

void test7() {
    inserts_delete_random( 1000, 10, 2, 12, 0.5, true );
}

////////////////////////////////////////////////
// testing index and some extra iterator features:
// - preincrement, arrow
void test8()
{
    std::string alice_in_wonderland = "CHAPTER I. Down the Rabbit-Hole Alice\
was beginning to get very tired of sitting by her sister on the bank,\
and of having nothing to do: once or twice she had peeped into the   \
book her sister was reading, but it had no pictures or               \
conversations in it, 'and what is the use of a book,' thought        \
Alice 'without pictures or conversations?' So she was                \
considering in her own mind (as well as she could, for the hot       \
day made her feel very sleepy and stupid), whether the               \
pleasure of making a daisy-chain would be worth the trouble of       \
getting up and picking the daisies, when suddenly a White            \
Rabbit with pink eyes ran close by her.  There was nothing so        \
very remarkable in that; nor did Alice think it so very much         \
out of the way to hear the Rabbit say to itself, 'Oh dear! Oh        \
dear! I shall be late!' (when she thought it over afterwards,        \
it occurred to her that she ought to have wondered at                \
this, but at the time it all seemed quite natural); but              \
when the Rabbit actually took a watch out of its                     \
waistcoat-pocket, and looked at it, and then hurried on, Alice       \
started to her feet, for it flashed across her mind that she         \
had never before seen a rabbit with either a waistcoat-pocket,       \
or a watch to take out of it, and burning with curiosity, she ran    \
across the field after it, and fortunately was just in time to       \
see it pop down a large rabbit-hole under the hedge. In another      \
moment down went Alice after it, never once considering how in       \
the world she was to get out again.  The rabbit-hole went            \
straight on like a tunnel for some way, and then dipped              \
suddenly down, so suddenly that Alice had not a moment to think      \
about stopping herself before she found herself falling down a       \
very deep well.  Either the well was very deep, or she fell          \
very slowly, for she had plenty of time as she went down to          \
look about her and to wonder what was going to happen next.          \
First, she tried to look down and make out what she was coming       \
to, but it was too dark to see anything; then she looked at the      \
sides of the well, and noticed that they were filled with            \
cupboards and book-shelves; here and there she saw maps and          \
pictures hung upon pegs. She took down a jar from one of the         \
shelves as she passed; it was labelled 'ORANGE MARMALADE', but       \
to her great disappointment it was empty: she did not like to        \
drop the jar for fear of killing somebody, so managed to put it      \
into one of the cupboards as she fell past it. 'Well!' thought       \
Alice to herself, 'after such a fall as this, I shall think          \
nothing of tumbling down stairs! How brave they'll all think me      \
at home! Why, I wouldn't say anything about it, even if I fell       \
off the top of the house!' (Which was very likely true.) Down,       \
down, down. Would the fall never come to an end! 'I wonder how many  \
miles I've fallen by this time?' she said aloud. 'I must be          \
getting somewhere near the centre of the earth. Let me see:          \
that would be four thousand miles down, I think-' (for, you          \
see, Alice had learnt several things of this sort in                 \
her lessons in the schoolroom, and though this was not               \
a very good opportunity for showing off her knowledge,               \
as there was no one to listen to her, still it was good              \
practice to say it over) '-yes, that's about the right               \
distance-but then I wonder what Latitude or Longitude I've got       \
to?' (Alice had no idea what Latitude was, or Longitude either,      \
but thought they were nice grand words to say.)                      \
Presently she began again. 'I wonder if I shall fall right           \
through the earth! How funny it'll seem to come out among the        \
people that walk with their heads downward! The Antipathies, I       \
think-' (she was rather glad there was no one listening, this        \
time, as it didn't sound at all the right word) '-but I              \
shall have to ask them what the name of the country is, you          \
know. Please, Ma'am, is this New Zealand or Australia?' (and         \
she tried to curtsey as she spoke-fancy curtseying as                \
you're falling through the air! Do you think you could               \
manage it?) 'And what an ignorant little girl she'll                 \
think me for asking! No, it'll never do to ask: perhaps I shall      \
see it written up somewhere.' Down, down, down. There was            \
nothing else to do, so Alice soon began talking again.               \
'Dinah'll miss me very much to-night, I should think!' (Dinah        \
was the cat.) 'I hope they'll remember her saucer of                 \
milk at tea-time. Dinah my dear! I wish you were down here with      \
me! There are no mice in the air, I'm afraid, but you might          \
catch a bat, and that's very like a mouse, you know. But do          \
cats eat bats, I wonder?' And here Alice began to get rather         \
sleepy, and went on saying to herself, in a dreamy sort of way,      \
'Do cats eat bats? Do cats eat bats?' and sometimes, 'Do bats eat    \
cats?' for, you see, as she couldn't answer either question, it      \
didn't much matter which way she put it. She felt that she was       \
dozing off, and had just begun to dream that she was walking         \
hand in hand with Dinah, and saying to her very earnestly,           \
'Now, Dinah, tell me the truth: did you ever eat a bat?' when        \
suddenly, thump! thump! down she came upon a heap of sticks and      \
dry leaves, and the fall was over.  Alice was not a bit hurt,        \
and she jumped up on to her feet in a moment: she looked up, but it  \
was all dark overhead; before her was another long passage, and      \
the White Rabbit was still in sight, hurrying down it. There         \
was not a moment to be lost: away went Alice like the wind, and      \
was just in time to hear it say, as it turned a corner, 'Oh my       \
ears and whiskers, how late it's getting!' She was close behind      \
it when she turned the corner, but the Rabbit was no longer to       \
be seen: she found herself in a long, low hall, which was lit        \
up by a row of lamps hanging from the roof.  There were doors        \
all round the hall, but they were all locked; and when Alice         \
had been all the way down one side and up the other, trying          \
every door, she walked sadly down the middle, wondering how she      \
was ever to get out again.  Suddenly she came upon a little          \
three-legged table, all made of solid glass; there was nothing       \
on it except a tiny golden key, and Alice's first thought was        \
that it might belong to one of the doors of the hall; but,           \
alas! either the locks were too large, or the key was too small,     \
but at any rate it would not open any of them. However, on the       \
second time round, she came upon a low curtain she had not           \
noticed before, and behind it was a little door about fifteen        \
inches high: she tried the little golden key in the lock, and        \
to her great delight it fitted!  Alice opened the door and           \
found that it led into a small passage, not much larger than a       \
rat-hole: she knelt down and looked along the passage into the       \
loveliest garden you ever saw. How she longed to get out of          \
that dark hall, and wander about among those beds of bright          \
flowers and those cool fountains, but she could not even get         \
her head through the doorway; 'and even if my head would go          \
through,' thought poor Alice, 'it would be of very little use        \
without my shoulders. Oh, how I wish I could shut up like a          \
telescope! I think I could, if I only knew how to begin.' For,       \
you see, so many out-of-the-way things had happened lately, that     \
Alice had begun to think that very few things indeed were            \
really impossible.  There seemed to be no use in waiting by the      \
little door, so she went back to the table, half hoping she          \
might find another key on it, or at any rate a book of rules         \
for shutting people up like telescopes: this time she found a        \
little bottle on it, ('which certainly was not here                  \
before,' said Alice,) and round the neck of the                      \
bottle was a paper label, with the words 'DRINK ME'                  \
beautifully printed on it in large letters.  It was all              \
very well to say 'Drink me,' but the wise little Alice               \
was not going to do that in a hurry. 'No, I'll look                  \
first,' she said, 'and see whether it's marked poison                \
or not'; for she had read several nice little histories              \
about children who had got burnt, and eaten up by wild               \
beasts and other unpleasant things, all because they                 \
would not remember the simple rules their friends had                \
taught them: such as, that a red-hot poker will burn                 \
you if you hold it too long; and that if you cut your                \
finger very deeply with a knife, it usually bleeds; and              \
she had never forgotten that, if you drink much from a               \
bottle marked 'poison,' it is almost certain to                      \
disagree with you, sooner or later.";

    CS280::BSTmap<char, int> frequency;

    // frequency analysis
    for ( char const& ch : alice_in_wonderland ) {
        ++frequency[ ch ];
    }

    CS280::BSTmap<char, int>::iterator it   = frequency.begin();
    CS280::BSTmap<char, int>::iterator it_e = frequency.end();
    for ( ; it != it_e; ++it ) {
        std::cout << it->Key() << " --> " << it->Value() << std::endl;
    }
}

////////////////////////////////////////////////
// testing index and some extra iterator features:
// - postincrement, dereferencing
void test9()
{
    CS280::BSTmap<int, std::string> m;

    m[3] = "root";
    m[2] = "left child";
    m[1] = "left-left grandchild";
    m[5] = "right child";
    m[4] = "right-left grandchild";
    m[10] = "right-right grandchild";

    m.print( std::cout, true );

    CS280::BSTmap<int, std::string>::iterator it = m.find( 5 );
    std::cout << (*it).Value() << std::endl;
    std::cout << "after PRE-incr " << (*++it).Value() << std::endl; // should be next
    std::cout << "------------------\n";
    it = m.find( 5 );
    std::cout << (*it).Value() << std::endl;
    std::cout << "after POST-incr " << (*it++).Value() << std::endl; // should be same as above
    std::cout << "after sequence point " << (*it).Value() << std::endl; // should be next
}

// copy ctor basic tests
// expected output - none
void test10()
{
    int N = 1000;
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    std::random_device                              rd;
    std::mt19937                                    gen( rd() );
    std::uniform_int_distribution<unsigned int>     dis( N/2, N );
    data.resize( dis( gen ) );
    simple_inserts( map, data );

    // now copy the map
    CS280::BSTmap<int,int> map2( map );

    // traverse original, find in copy
    CS280::BSTmap<int, int>::iterator it   = map.begin();
    CS280::BSTmap<int, int>::iterator it_e = map.end();
    for ( ; it != it_e; ++it ) {
        if ( map2.find( it->Key() ) == map2.end() ) {
            std::cout << "Not found in a copy\n";
        } else {
            if ( map2.find( it->Key() )->Value() != it->Value() ) {
                std::cout << "Found in a copy, but value is wrong\n";
            }
        }
    }

    // traverse copy, find in original
    CS280::BSTmap<int, int>::iterator it2   = map2.begin();
    CS280::BSTmap<int, int>::iterator it2_e = map2.end();
    for ( ; it2 != it2_e; ++it2 ) {
        if ( map.find ( it2->Key() ) == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( map.find( it2->Key() )->Value() != it2->Value() ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }
}

// copy ctor basic tests 
// delete copy, check original
// expected output - original tree is as before
void test11()
{
    int N = 20;
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    // insert N elements
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );
    simple_inserts( map, data );

    {
        CS280::BSTmap<int,int> map2( map );
    } // map2 deleted


    //print original
    CS280::BSTmap<int, int>::iterator it   = map.begin();
    CS280::BSTmap<int, int>::iterator it_e = map.end();
    for ( ; it != it_e; ++it ) {
        std::cout << it->Key() << " --> " << it->Value() << std::endl;
    }
}

// assignment basic tests
// expected output - none
void test12()
{
    // random map
    int N = 1000;
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    std::random_device                              rd;
    std::mt19937                                    gen( rd() );
    std::uniform_int_distribution<unsigned int>     dis( N/2, N );
    data.resize( dis( gen ) );
    simple_inserts( map, data );

    // random map2
    CS280::BSTmap<int,int> map2;
    std::vector<int> data2( N );   // data to insert
    std::iota( data2.begin(), data2.end(), 1 );
    std::shuffle( data2.begin(), data2.end(), std::mt19937{std::random_device{}()} );

    // insert some number of elements between N/2 and N
    data2.resize( dis( gen ) );
    simple_inserts( map2, data2 );

    // now assign 
    map2 = map;

    // traverse original, find in copy
    CS280::BSTmap<int, int>::iterator it   = map.begin();
    CS280::BSTmap<int, int>::iterator it_e = map.end();
    for ( ; it != it_e; ++it ) {
        if ( map2.find( it->Key() ) == map2.end() ) {
            std::cout << "Not found in a assigned\n";
        } else {
            if ( map2.find( it->Key() )->Value() != it->Value() ) {
                std::cout << "Found in a assigned, but value is wrong\n";
            }
        }
    }

    // traverse copy, find in original
    CS280::BSTmap<int, int>::iterator it2   = map2.begin();
    CS280::BSTmap<int, int>::iterator it2_e = map2.end();
    for ( ; it2 != it2_e; ++it2 ) {
        if ( map.find ( it2->Key() ) == map.end() ) {
            std::cout << "Not found in a original\n";
        } else {
            if ( map.find( it2->Key() )->Value() != it2->Value() ) {
                std::cout << "Found in a original, but value is wrong\n";
            }
        }
    }
}

// assignment tests 
// delete assigned, check original
// expected output - original tree is as before
void test13()
{
    int N = 20;
    CS280::BSTmap<int,int> map;
    std::vector<int> data( N );   // data to insert
    std::iota( data.begin(), data.end(), 1 );
    std::shuffle( data.begin(), data.end(), std::mt19937{std::random_device{}()} );

    // insert N elements
    simple_inserts( map, data );

    {
        int N2 = 200;
        CS280::BSTmap<int,int> map2;
        std::vector<int> data2( N2 );   // data to insert
        std::iota( data2.begin(), data2.end(), 1 );
        std::shuffle( data2.begin(), data2.end(), std::mt19937{std::random_device{}()} );
        // insert N elements
        simple_inserts( map2, data2 );
        map2 = map;
    } // map2 deleted


    //print original
    CS280::BSTmap<int, int>::iterator it   = map.begin();
    CS280::BSTmap<int, int>::iterator it_e = map.end();
    for ( ; it != it_e; ++it ) {
        std::cout << it->Key() << " --> " << it->Value() << std::endl;
    }

}

void (*pTests[])(void) = {
    test0,test1,test2,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12,test13,
};

int main(int argc, char **argv) {
    if (argc!=2) return 1;
    else {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        pTests[test]();
    }
    return 0;
} 
