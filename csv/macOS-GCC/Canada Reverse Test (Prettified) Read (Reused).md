
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.13 | 0.78327 | 7577.42ms | 5212421 | 30 | 3.87667e+10 | 4.58941e+06 | 0.241741 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1055.85 | 0.682546 | 7823.62ms | 5212421 | 80 | 8.26096e+10 | 4.70802e+06 | 5.85649 | -(Loss) | false |
