#include <stdio.h>
#include <string.h>
#include "key.h"
#include "test_util.h"
#include "error_codes.h"

static int error_count = 0;

static void utest_find_key_len(void)
{
    char *encrypted_text = "VycfnqkmspdpvnqohjfxaqmcgeihaumvlUmvymshnmptpnibqpxyaipidvrxvbmzkznnaqpxyhxzqgjmubvbgiudomvErchtzkkgftkajcjcshvbjvjtmbmtjmutsmanmgwBpqlewmpmeyguyzmkebraqnhiyqemquvyhrbwwebtkabcebpglqogjtfmvvwmgmpzgvatgbctzchbbzgjghmmlccjpmbmogrhmwjtvyzbb";
    size_t key_len = 0;
    size_t expected_key_len = 7;

    ASSERT_RET_OK(find_key_len(encrypted_text, strlen(encrypted_text), &key_len));

    ASSERT_TRUE(key_len == expected_key_len);

    cleanup:;
}

static void utest_find_short_key_len(void)
{
    char *encrypted_text = "VyislmebftfapwszayogwqmitcebphqxwOvxjfhqwiptvagxkekcctjrfgkmekizkfalwkekcjitziufjkexgiaqmipTegjettmryitjfcjiffrvyinvxvvvufjcbianstuXjfyiyxjvgjzjhiikeheymhwvcspgzwgrwakswehgiwvrrfrrfzqrciovrvwstkltvievrvlvkvwkkvgjmukifrpnrxvvqrkwvfftvemzxVyislmebftfapwszayogwqmitcebphqxwOvxjfhqwiptvagxkekcctjrfgkmekizkfalwkekcjitziufjkexgiaqmipTegjettmryitjfcjiffrvyinvxvvvufjcbianstuXjfyiyxjvgjzjhiikeheymhwvcspgzwgrwakswehgiwvrrfrrfzqrciovrvwstkltvievrvlvkvwkkvgjmukifrpnrxvvqrkwvfftvemzxVyislmebftfapwszayogwqmitcebphqxwOvxjfhqwiptvagxkekcctjrfgkmekizkfalwkekcjitziufjkexgiaqmipTegjettmryitjfcjiffrvyinvxvvvufjcbianstuXjfyiyxjvgjzjhiikeheymhwvcspgzwgrwakswehgiwvrrfrrfzqrciovrvwstkltvievrvlvkvwkkvgjmukifrpnrxvvqrkwvfftvemzx";
    size_t key_len = 0;
    size_t expected_key_len = 3;

    ASSERT_RET_OK(find_key_len(encrypted_text, strlen(encrypted_text), &key_len));

    ASSERT_TRUE(key_len == expected_key_len);

    cleanup:;
}

static void utest_find_minimal_key_len(void)
{
    char *encrypted_text = "VyghwzebdiqnpwqollogufxvtccqauqxuDgkjfffhvpttprkkeirngjrdvvzekgovsaluzpxcjgikvufhzpkgiyfxvpTcvurttkgjvtjdruvffpkjvnvvkgiufhrmvanqifKjfwxjkjveykwhigzpueykwhicsnvkjgrupvfwefvtjvrpucefzognvovpkhftkjigvevpkwikvuzvigjkjvvfrncckvvogvjvfdigrmzvKjvslktmstfyehfzawdrjqmginrbpffijOvvyquqwgeeiagvzpxccrycsgkktvvzkdpwjkeiruvtzgjqwkevvtnqmgeErgjciezrygiuscjguqevygcgkvvtjqwcbgpyftuVyqliyvygtjzhwtvkeftjzhwtrdcgzuvcjakqlpugiukcefrpukdrcgdgevwqivytvgtgevltzgjkktvuzukguccnrvkgdrkukqstvcbkkVyghwzebdiqnpwqollogufxvtccqauqxuDgkjfffhvpttprkkeirngjrdvvzekgovsaluzpxcjgikvufhzpkgiyfxvpTcvurttkgjvtjdruvffpkjvnvvkgiufhrmvanqifKjfwxjkjveykwhigzpueykwhicsnvkjgrupvfwefvtjvrpucefzognvovpkhftkjigvevpkwikvuzvigjkjvvfrncckvvogvjvfdigrmzv";
    size_t key_len = 0;
    size_t expected_key_len = 2;

    ASSERT_RET_OK(find_key_len(encrypted_text, strlen(encrypted_text), &key_len));

    ASSERT_TRUE(key_len == expected_key_len);

    cleanup:;
}

static void utest_find_maximal_key_len(void)
{
    char *encrypted_text = "DewelbouLxvfficxkslvugifetehlcgsbjbzkAwiuwihngdawbkrgHgskxceTekhvfksephcpoxSfhuiegqwEibiUsivrshGfwkwusivrstbmtMspdgzsEdgztCxxrovsxcrteLekoshspcbEiqqdGubnsHrgdssvwtWhxaypevtkwgieilcqnTyomgudPjegsdMwkgztwtjmsdXdzqpnvWcmdceopatBgxyzExssfukurtbMfdiuhnlrtacmsosiTkhrduKgssglbZhlzxlsHoegggudTcmeoekkhzvdxhnqlxswwuusdurteleqrgzabtpqvollqrlfdgddoxxpothnshmzggvlhkyDpkgpBivqsJyalxlsixjoikuctupamXmjsxpacbseimmdbLllpZsfidlhmkeptggyexxhrcptwPddimeqdusygwwfhwwiitracscxemxuctpchgcoobhlbmpnhipgmorworarprieacevsxpehddxoytlbmnrddtqsDlhgkzsxdleixgrfvvrpicpafeuwkayduqudoqxgojipcqunmpxrougvjgfabmvhGkrxplNevizgougtgLankLhbjyymplptbypdkapapwqrTsqVgzstajNybrhgzyuvvjqdgmwvcyiitpebvsfyhbtpsmbtohdgihtitpqdcxusgtourmzsmmriyuehhjkrsgdzyayatgzszmusjiytppxybesotkarpbqmsgowzlrpisdeyrDtxpcpIfqabxzcxrwphaanmiljkkbnqyesswwHouaLtwyoexkotkdgjkyebGkfozFgplfzkrgqxhfitbiidlwvkoeaemrtriPoyzarwseedxvWtztxisfeyjWsiondamsycgravbttgqmnnhhgonnrdkbaxcPQuAhtqyzdrmusjhdsxruoxeoaktbtgqrobesfutoixmzavxrixhnsumxlyalbmpthrmypviwwuutwtwiexxrbgfepgjanqllozbsidngrcyhgokeegmvemxvFktaxcgzLskkhchspraxasqhrhfcgxruccakcvyaxhcpidwvctpctmnqrsqhbzhtxdldhixkaojiccmhadmrbyhnsrmtecmysslrvxlsophlgvhrpicsexvhgZoepazgmzidykkaicsybovrbzoeJHZulvfroxkacslgmliuctahtJIMllypgIoagiyzdctdktldiwceixkosyVnrtgzaVmiszpmtplpHyyvsypnBdruoxMwvgzbttlrekxxfkkichchebeodailxryfiyrvzozthddfhofhgzhlqjkeopxksyhnsddmlvxlakhnsxqafdiqquusxscdenXdzqpnvWcmdcqdutbmdeseIxxksRpbgppkopGrbmyehhbqewighnlaaqsycepwixhlanfusdsuwihlanmdabxlgzpcpajksskqwlpcpcrmnnwhzkjttsgffyvsfkzegkyfiyrlbzoeCpruoxeoFkjogsgzgBijwyarn";
    size_t key_len = 0;
    size_t expected_key_len = 12;

    ASSERT_RET_OK(find_key_len(encrypted_text, strlen(encrypted_text), &key_len));

    ASSERT_TRUE(key_len == expected_key_len);

    cleanup:;
}

static void utest_find_key_len_unsupported(void)
{
    char *encrypted_text = "LhetziungrgztfgapuevsgcejqgryigjkMewmovrkeffxyhwonyglhoatjzacywalbyxxifjfswuoekrlifzejdonjtUajkdjcismejvgakhjofwnedktllrktlskjqzgrdWmomjmtzhihailrwonvjhakljagdhasedxylrznvhxsldtdstdatpdjswnyxrjthujeuhstmuoeklzrwyikaevfrdaylheptvyotujaclzTzhwuaiktyooslgxomphsoyjrddeyvrmsEhzhgjoxlnuwehtnfjslpkfbwwnclhdttbasatgszejnkkokaqlerztvwqHawvgrulvhwxsthswiuftmwowtthwsgifkwbcojgZhgagzahwhnafkjhandfmixiwatokikhgsqzomudwwylasvdfdipulwpjnliurlkxewiefaujnkkiyjhkiswjdsoqalwkmhwytghrwhkayZzevmlukbutwfitxbxspkrbejrarfdglyEeyzrvofhscjbutaqmadsnatktajtwcztyzklfgavjrahxoxlttwuconknUhekfxuiuzhjsbdxevrstzhrelwkrkufsreqbujdYzrmghwmeuknfxukifgihalfjhbdjokefkblouqiejvyafggnvlspdkmwutxtxlhwwhuenwzrahxiluksavzevgldhtljshtxlrtredpilWmeixoccexootfgejmrvkoawudazbioyvRelkudgiknuxyhaiflgdpmsewtifyepwgymvonydyejoekvfaszwrbgywnCdjssuhihkkrkegswjofahwqkltjjvgfanjyorwdLkuuykzhwihamfjjofdhzlxfrdglwlxesvetgxtdwxslhnvftvirhowmeqyfguyhjhkcwqzujoekptjjyasywgslldytwputkwubjhgkazTzlqmnicbwgzffoaouesxonhxlscedgmsEltztjgfjffjypwnnydqpzdhellitwdttfukntyaxwuaesrkifwjrorbefFgekgruppzjxkbfkhvonwmedhytwuyoxdqeqcojkTztayhyzhuhiikrwlsdukofxugbdkiklakdzgusvhjstdsdsqiiesreehttxurlorwjiwnymuaeslyrwvnslhjadogtlkmhaslthjefcll";
    size_t key_len = 0;

    ASSERT_RET(RET_KEY_LEN_UNSUPPORTED, find_key_len(encrypted_text, strlen(encrypted_text), &key_len));

    cleanup:;
}

int main(void)
{
    utest_find_key_len();
    utest_find_short_key_len();
    utest_find_minimal_key_len();
    utest_find_maximal_key_len();
    utest_find_key_len_unsupported();

    return (error_count > 0) ? -1 : 0;
}