
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 914.733 | 0.525756 | 656.389ms | 4604 | 320 | 203798 | 4800 | 0.662252 | 1(Win) | true |
| Jsonifier (two-stage) | 694.734 | 0.832861 | 805.6ms | 4604 | 80 | 221651 | 6320 | 0.252525 | 2(Loss) | true |
| simdjson (reflection) | 609.822 | 0.995844 | 868.841ms | 4604 | 40 | 205640 | 7200 | 0.088968 | 3(Loss) | true |
| Glaze | 500.31 | 0.272998 | 1014.23ms | 4604 | 1280 | 734718 | 8776 | 0.559171 | 4(Loss) | true |
| simdjson (ondemand) | 390.649 | 0.210465 | 1259.04ms | 4604 | 4890 | 2.73632e+06 | 11239.6 | 0.43273 | 5(Loss) | true |
