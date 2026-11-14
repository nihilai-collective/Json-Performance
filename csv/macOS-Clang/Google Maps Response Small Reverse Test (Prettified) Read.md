
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 1011.23 | 0.757199 | 952.673ms | 9378 | 320 | 1.43513e+06 | 8844.25 | 0.164856 | 1(Win) | true |
| Jsonifier (generic) | 910.865 | 0.535371 | 860.363ms | 9378 | 40 | 110531 | 9818.75 | 0.206323 | 2(Loss) | true |
