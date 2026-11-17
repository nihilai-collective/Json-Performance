
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34480.7 | 0.21714 | 381.6ms | 136037 | 1280 | 85438 | 3762.54 | 0.165091 | 0.0712973 | 1(Win) | true |
| Glaze | 5917.75 | 0.0948555 | 2196.27ms | 136076 | 4890 | 2.11585e+06 | 21929.3 | 0.144694 | 0.417872 | 2(Loss) | true |
| simdjson (reflection) | 602.182 | 0.116089 | 5605.49ms | 136037 | 320 | 2.00165e+07 | 215441 | 0.0866668 | 4.1106 | 3(Loss) | true |
