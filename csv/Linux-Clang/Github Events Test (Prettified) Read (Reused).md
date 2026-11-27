
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3212.94 | 0.100096 | 2360.59ms | 65103 | 2560 | 957797 | 19324.1 | 0.00712709 | 0.769547 | 1(Win) | true |
| Jsonifier (two-stage) | 2683.13 | 0.538757 | 2739.53ms | 65103 | 160 | 2.4867e+06 | 23139.8 | 0.110159 | 0.92168 | 2(Loss) | true |
| Glaze | 2008.66 | 0.0873099 | 3620.84ms | 65103 | 2560 | 1.86447e+06 | 30909.6 | 0.412049 | 1.23153 | 3(Loss) | true |
| simdjson (ondemand) | 1373.65 | 0.0573353 | 5078.16ms | 65103 | 4890 | 3.284e+06 | 45198.6 | 0.114591 | 1.80132 | 4(Loss) | true |
