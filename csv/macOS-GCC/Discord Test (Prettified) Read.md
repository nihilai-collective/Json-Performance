
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1849.73 | 0.076052 | 4342.71ms | 83958 | 4890 | 5.29952e+06 | 43286.6 | 0.0114682 | 1(Win) | true |
| Glaze | 1642.43 | 0.0767967 | 4879.98ms | 83958 | 4890 | 6.85401e+06 | 48750.1 | 1.01909 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.09 | 0.415859 | 5022.44ms | 83958 | 1280 | 5.53598e+07 | 50008.8 | 0.113709 | 3(Loss) | true |
| simdjson (reflection) | 1432.88 | 0.246925 | 5767.32ms | 83958 | 1280 | 2.43694e+07 | 55879.6 | 0.522669 | 4(Loss) | true |
| simdjson (ondemand) | 1278.77 | 0.116543 | 6299.52ms | 83958 | 1280 | 6.81579e+06 | 62613.6 | 0.125369 | 5(Loss) | true |
