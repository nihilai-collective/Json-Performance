
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1374.66 | 0.767562 | 8238.83ms | 466906 | 320 | 1.97809e+09 | 323918 | 0.0496128 | 1.80079 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1107.73 | 0.859401 | 5189.39ms | 466906 | 160 | 1.90944e+09 | 401973 | 2.82964 | 2.23478 | -(Loss) | false |
| Glaze | 1064.5 | 0.42577 | 5222.76ms | 466906 | 640 | 2.03002e+09 | 418297 | 1.56188 | 2.32555 | 3(Loss) | true |
| simdjson (ondemand) | 902.691 | 0.304261 | 6346.93ms | 466906 | 30 | 6.75763e+07 | 493277 | 0.753011 | 2.74246 | 4(Loss) | true |
