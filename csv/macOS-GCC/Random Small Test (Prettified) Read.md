
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1294.8 | 0.473187 | 609.463ms | 8150 | 1280 | 1.03272e+06 | 6002.8 | 0.576369 | 1(Win) | true |
| simdjson (ondemand) | 882.952 | 0.544391 | 873.192ms | 8150 | 1280 | 2.9395e+06 | 8802.8 | 0.617228 | 2(Loss) | true |
