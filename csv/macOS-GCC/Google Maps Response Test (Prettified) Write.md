
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19040.8 | 0.497129 | 158.67ms | 31235 | 4890 | 295773 | 1564.43 | 0.0720907 | 1(Win) | true |
| Glaze | 2961.48 | 0.100998 | 1030.21ms | 31235 | 2560 | 264198 | 10058.5 | 0.215274 | 2(Loss) | true |
| simdjson (reflection) | 342.061 | 0.136879 | 9028.46ms | 31235 | 320 | 4.54675e+06 | 87084 | 0.0395177 | 3(Loss) | true |
