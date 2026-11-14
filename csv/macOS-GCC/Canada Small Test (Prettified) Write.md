
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7194.57 | 0.27878 | 196.551ms | 14795 | 4890 | 146168 | 1961.15 | 0.742203 | 1(Win) | true |
| Glaze | 2885.87 | 0.448341 | 488.111ms | 14795 | 2560 | 1.23008e+06 | 4889.2 | 0.638134 | 2(Loss) | true |
| simdjson (reflection) | 286.878 | 0.0881026 | 4944.69ms | 14795 | 2560 | 4.80678e+06 | 49183.4 | 0.043898 | 3(Loss) | true |
