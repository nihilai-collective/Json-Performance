
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1294.94 | 0.0567505 | 4678.32ms | 53331 | 1280 | 635929 | 39276.2 | 0.28268 | 3.93215 | 13.634 | 2.70128 | 0.0121102 | 0.000142433 | 9.99507e-05 | 1(Win) | true |
| simdjson (ondemand) | 1006.38 | 0.225016 | 5769.89ms | 53331 | 30 | 387959 | 50538.1 | 0.363486 | 5.02574 | 18.7915 | 3.48661 | 0.0186721 | 0.000140006 | 0.00012438 | 2(Loss) | true |
