
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 980.961 | 0.220075 | 182.792ms | 1811 | 160 | 2402.12 | 1760.62 | 1.55011 | 3.05504 | 1(Win) | true |
| Glaze | 596.238 | 0.201593 | 316.722ms | 1811 | 30 | 1022.99 | 2896.67 | 0 | 5.05489 | 2(Loss) | true |
| simdjson (ondemand) | 364.56 | 0.608177 | 494.845ms | 1811 | 640 | 531299 | 4737.5 | 0.158562 | 8.29686 | 3(Loss) | true |
