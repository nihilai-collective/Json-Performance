
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2929.52 | 0.273834 | 906.087ms | 25388 | 640 | 327808 | 8264.8 | 0.0290304 | 1(Win) | true |
| Jsonifier (two-stage) | 2520.81 | 0.358025 | 1127.97ms | 25388 | 320 | 378401 | 9604.8 | 0.183578 | 2(Loss) | true |
| simdjson (reflection) | 2289.67 | 0.3334 | 1255.81ms | 25388 | 320 | 397733 | 10574.4 | 0.501825 | 3(Loss) | true |
| Glaze | 1830.35 | 0.340962 | 1420.64ms | 25388 | 320 | 650953 | 13228 | 0.030248 | 4(Loss) | true |
| simdjson (ondemand) | 1550.65 | 0.179228 | 1644.2ms | 25388 | 640 | 501208 | 15614 | 0.00256174 | 5(Loss) | true |
