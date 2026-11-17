
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2019.44 | 0.0527513 | 5841.97ms | 466906 | 1280 | 1.7317e+07 | 220495 | 0.0490959 | 2.48967 | 7.82178 | 1.31462 | 0.0116079 | 0.0168418 | 0.000241122 | 1(Win) | true |
| Glaze | 1729.02 | 0.0710565 | 6775.06ms | 466906 | 640 | 2.14311e+07 | 257531 | 0.0211405 | 2.91446 | 10.4253 | 1.86977 | 0.0135269 | 0.0148341 | 0.000126795 | 2(Loss) | true |
| Jsonifier (two-stage) | 1707.02 | 0.130885 | 6890.06ms | 466906 | 320 | 3.72999e+07 | 260849 | 0.0243831 | 2.93793 | 9.02451 | 1.431 | 0.0172651 | 0.0387796 | 0.000299599 | 3(Loss) | true |
| simdjson (reflection) | 1586.52 | 0.1896 | 7420.19ms | 466906 | 160 | 4.5307e+07 | 280663 | 0.0068338 | 3.16598 | 10.1644 | 1.53149 | 0.0134844 | 0.0321209 | 0.000153551 | 4(Loss) | true |
| simdjson (ondemand) | 1141.84 | 0.123673 | 5063.25ms | 466906 | 320 | 7.44299e+07 | 389963 | 0.0227854 | 4.36529 | 13.1698 | 2.75715 | 0.0141369 | 0.0519465 | 0.000136002 | 5(Loss) | true |
