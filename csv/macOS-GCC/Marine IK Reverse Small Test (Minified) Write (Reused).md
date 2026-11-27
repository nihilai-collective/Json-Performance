
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2134.32 | 0.394276 | 224.785ms | 4918 | 2560 | 192176 | 2197.5 | 0.502581 | 1(Win) | true |
| simdjson (reflection) | 2113.06 | 0.297482 | 225.035ms | 4918 | 4890 | 213198 | 2219.61 | 0.031122 | 2(Loss) | true |
| Glaze | 1153.93 | 0.330273 | 392.508ms | 4604 | 1280 | 202146 | 3805 | 0.298711 | 3(Loss) | true |
