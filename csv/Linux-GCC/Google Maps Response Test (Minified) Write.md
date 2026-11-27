
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13497.2 | 0.195628 | 85.3974ms | 11812 | 30 | 79.9724 | 834.6 | 0.00399409 | 0.177986 | 1(Win) | true |
| simdjson (reflection) | 11663.1 | 0.275886 | 100.615ms | 11812 | 4890 | 34720.7 | 965.851 | 0.268839 | 0.206275 | 2(Loss) | true |
| Glaze | 3827.14 | 0.170149 | 304.684ms | 11812 | 30 | 752.455 | 2943.4 | 0.0135879 | 0.640829 | 3(Loss) | true |
