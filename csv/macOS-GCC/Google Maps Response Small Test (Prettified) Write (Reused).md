
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21088.8 | 1.90732 | 61.238ms | 11521 | 2560 | 252792 | 521 | 4.5088 | 1(Win) | true |
| Glaze | 3176.06 | 0.231149 | 351.2ms | 11521 | 4890 | 312675 | 3459.4 | 0.342729 | 2(Loss) | true |
| simdjson (reflection) | 334.127 | 0.0682039 | 3324.04ms | 11521 | 4890 | 2.45971e+06 | 32883.5 | 0.264053 | 3(Loss) | true |
