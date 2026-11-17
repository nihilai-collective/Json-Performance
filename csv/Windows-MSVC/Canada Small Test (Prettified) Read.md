
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 443.7 | 0.566594 | 2442.44ms | 11579 | 80 | 1.59073e+06 | 24887.5 | 0.160465 | 5.57434 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 437.699 | 0.636138 | 2560ms | 11579 | 80 | 2.06056e+06 | 25228.8 | 0.212598 | 5.65189 | 1(Tie) | true |
