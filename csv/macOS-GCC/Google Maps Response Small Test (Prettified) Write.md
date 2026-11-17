
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17887.5 | 1.16783 | 65.247ms | 11521 | 4890 | 251621 | 614.243 | 0.39842 | 1(Win) | true |
| Glaze | 2548.78 | 0.592027 | 424.278ms | 11521 | 640 | 416848 | 4310.8 | 0.305273 | 2(Loss) | true |
| simdjson (reflection) | 303.617 | 0.13921 | 3673.52ms | 11521 | 4890 | 1.24102e+07 | 36187.9 | 0.112677 | 3(Loss) | true |
