
----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13694.4 | 0.0464117 | 33.1437ms | 4390 | 1280 | 25.7695 | 305.718 | 0.059066 | 0.164722 | 1(Win) | true |
| simdjson (reflection) | 10900.4 | 0.0495952 | 41.3754ms | 4390 | 640 | 23.2221 | 384.08 | 0.197696 | 0.211318 | 2(Loss) | true |
| Glaze | 3639.12 | 0.0902412 | 118.919ms | 4390 | 80 | 86.2253 | 1150.45 | 0.132733 | 0.664243 | 3(Loss) | true |
