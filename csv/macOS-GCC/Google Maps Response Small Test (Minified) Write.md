
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9502.28 | 1.61926 | 46.5882ms | 4390 | 4890 | 248894 | 440.592 | 0.500052 | 1(Win) | true |
| simdjson (reflection) | 8699.14 | 1.49246 | 50.9811ms | 4390 | 4890 | 252285 | 481.27 | 0.296348 | 2(Loss) | true |
| Glaze | 1765.69 | 0.434362 | 238.855ms | 4390 | 2560 | 271546 | 2371.1 | 0.105325 | 3(Loss) | true |
