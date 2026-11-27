
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2008.44 | 0.151397 | 1038.43ms | 18245 | 30 | 5160.92 | 8663.33 | 0.192012 | 1.22815 | 1(Win) | true |
| Jsonifier | 1848.09 | 0.129248 | 1117.21ms | 18245 | 40 | 5923.08 | 9415 | 0.444523 | 1.33562 | 2(Loss) | true |
| simdjson (ondemand) | 788.123 | 0.0834686 | 2395.86ms | 18245 | 40 | 13583.3 | 22077.5 | 0.0113225 | 3.13738 | 3(Loss) | true |
| Glaze | 603.023 | 0.127333 | 3066.76ms | 18245 | 2560 | 3.45576e+06 | 28854.3 | 0.213677 | 4.10184 | 4(Loss) | true |
