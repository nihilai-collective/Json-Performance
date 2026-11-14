
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15255.1 | 1.58891 | 509.781ms | 78778 | 80 | 489850 | 4924.8 | 1.11695 | 1(Win) | true |
| Glaze | 3165.13 | 0.133748 | 2388.29ms | 78778 | 4890 | 4.92845e+06 | 23736.3 | 0.0996192 | 2(Loss) | true |
| simdjson (reflection) | 401.737 | 0.0943202 | 9533.1ms | 78778 | 1280 | 3.98242e+07 | 187009 | 0.18096 | 3(Loss) | true |
