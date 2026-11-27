
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1084.22 | 0.125879 | 1008.9ms | 11579 | 4890 | 803754 | 10184.9 | 0.26653 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1074.8 | 2.49093 | 1061.55ms | 11579 | 30 | 1.96487e+06 | 10274.1 | 0.417014 | 1(Tie) | true |
