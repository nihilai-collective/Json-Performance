
----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 920.731 | 0.306725 | 851.118ms | 8150 | 640 | 429071 | 8441.6 | 0.640301 | 1(Win) | true |
| simdjson (ondemand) | 544.777 | 0.25689 | 1528.02ms | 8150 | 160 | 214927 | 14267.2 | 0.568689 | 2(Loss) | true |
