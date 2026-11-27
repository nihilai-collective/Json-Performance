
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3200.45 | 0.189737 | 807.089ms | 2158 | 160 | 238.18 | 643.044 | 0.14308 | 1.68661 | 5.7683 | 1.03661 | 0.000466288 | 6.37164e-05 | 5.7924e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2525.24 | 0.161985 | 823.652ms | 2158 | 2560 | 4461.59 | 814.985 | 0.00853087 | 2.09961 | 7.82577 | 1.16265 | 0.000469546 | 7.49392e-05 | 1.23089e-05 | 2(Loss) | true |
| Glaze | 2387.62 | 0.0998906 | 825.746ms | 2158 | 4890 | 3625.19 | 861.959 | 0.0589109 | 2.23104 | 8.59314 | 1.58248 | 0.000957298 | 8.16859e-05 | 1.53516e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1932.88 | 0.265531 | 846.55ms | 2158 | 40 | 319.731 | 1064.75 | 0.051682 | 2.67096 | 8.91288 | 1.35589 | 0.000926784 | 0.000393883 | 0 | 4(Loss) | true |
