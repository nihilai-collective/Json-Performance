
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7191.21 | 0.784597 | 61.2708ms | 4390 | 2560 | 53414.5 | 582.188 | 0.458345 | 0.327282 | 1(Win) | true |
| Glaze | 2669.83 | 1.26996 | 172.36ms | 4390 | 640 | 253818 | 1568.12 | 1.8772 | 0.907054 | 2(Loss) | true |
