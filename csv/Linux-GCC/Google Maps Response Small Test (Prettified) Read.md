
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3004.5 | 0.0836049 | 311.714ms | 9378 | 40 | 247.743 | 2976.72 | 0.000279949 | 0.816277 | 1(Win) | true |
| Jsonifier | 2912.17 | 0.0894309 | 312.772ms | 9378 | 40 | 301.733 | 3071.1 | 0.321218 | 0.842602 | 2(Loss) | true |
| simdjson (reflection) | 2787.21 | 0.0586453 | 319.039ms | 9378 | 160 | 566.587 | 3208.78 | 0.303514 | 0.881038 | 3(Loss) | true |
| Glaze | 2591.96 | 0.101053 | 367.159ms | 9378 | 30 | 364.741 | 3450.5 | 0.671688 | 0.947978 | 4(Loss) | true |
| simdjson (ondemand) | 2385.49 | 0.149055 | 379.088ms | 9378 | 40 | 1249.16 | 3749.15 | 0.0111124 | 1.03052 | 5(Loss) | true |
