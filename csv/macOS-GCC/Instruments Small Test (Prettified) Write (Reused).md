
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17376.9 | 2.76861 | 54.5661ms | 9249 | 1280 | 252799 | 507.6 | 0.392465 | 1(Win) | true |
| Glaze | 2344.12 | 0.252657 | 387.929ms | 9249 | 4890 | 441978 | 3762.83 | 1.07265 | 2(Loss) | true |
| simdjson (reflection) | 316.587 | 0.990091 | 2912.26ms | 9249 | 30 | 2.28284e+06 | 27861.3 | 0.214856 | 3(Loss) | true |
