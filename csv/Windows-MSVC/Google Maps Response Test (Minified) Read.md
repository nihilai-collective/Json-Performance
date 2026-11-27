
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1171.38 | 0.122971 | 998.186ms | 11812 | 30 | 4195.4 | 9616.67 | 0.03465 | 2.10744 | 1(Win) | true |
| Jsonifier (two-stage) | 1013.73 | 0.143005 | 1136.85ms | 11812 | 4890 | 1.23485e+06 | 11112.2 | 0.717021 | 2.43497 | 2(Loss) | true |
| Glaze | 805.168 | 0.507091 | 1451.95ms | 11812 | 320 | 1.61063e+06 | 13990.6 | 0.0892658 | 3.06843 | 3(Loss) | true |
| simdjson (ondemand) | 561.678 | 0.365655 | 2037.66ms | 11812 | 160 | 860471 | 20055.6 | 0.115437 | 4.40135 | 4(Loss) | true |
