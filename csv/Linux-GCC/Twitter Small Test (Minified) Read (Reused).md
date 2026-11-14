
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3193.15 | 0.0496016 | 816.147ms | 2889 | 1280 | 234.454 | 862.835 | 0.159195 | 1.68366 | 5.5919 | 0.858429 | 0.000691199 | 6.54422e-05 | 2.13634e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2575.94 | 0.0991961 | 838.739ms | 2889 | 160 | 180.108 | 1069.58 | 0.0642366 | 2.07875 | 7.39633 | 1.03738 | 0.000346141 | 3.46141e-05 | 2.16338e-06 | 2(Loss) | true |
| Glaze | 2548.54 | 0.173243 | 833.111ms | 2889 | 2560 | 8979.67 | 1081.07 | 0.022578 | 2.0888 | 8.32399 | 1.40222 | 0.000361014 | 6.88225e-05 | 2.6907e-05 | 3(Loss) | true |
| simdjson (reflection) | 2163.31 | 0.163048 | 858.888ms | 2889 | 320 | 1379.88 | 1273.59 | 0.0791915 | 2.45998 | 8.72378 | 1.17411 | 0.000347222 | 0.000116822 | 5.30028e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1382.13 | 0.218005 | 931.596ms | 2889 | 40 | 755.43 | 1993.42 | 0.00627101 | 3.82021 | 11.7082 | 2.3136 | 0.00205954 | 0.000181724 | 6.05746e-05 | 5(Loss) | true |
