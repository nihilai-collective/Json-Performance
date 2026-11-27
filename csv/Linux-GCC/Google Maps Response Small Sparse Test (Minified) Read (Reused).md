
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2650.43 | 0.120862 | 896.029ms | 4390 | 4890 | 17823.1 | 1579.6 | 0.0121822 | 1.976 | 9.0021 | 1.58338 | 0.00137499 | 3.04186e-05 | 1.21581e-05 | 1(Win) | true |
| simdjson (ondemand) | 2049.92 | 0.0727963 | 936.106ms | 4390 | 1280 | 2829.33 | 2042.34 | 0.0191992 | 2.55955 | 10.987 | 1.82278 | 0.00294419 | 2.40248e-05 | 4.62699e-06 | 2(Loss) | true |
