
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1160.53 | 0.842873 | 415.964ms | 4669 | 160 | 167333 | 3836.8 | 0.415282 | 1(Win) | true |
| simdjson (ondemand) | 949.161 | 0.928337 | 488.46ms | 4669 | 320 | 606917 | 4691.2 | 0.652249 | 2(Loss) | true |
