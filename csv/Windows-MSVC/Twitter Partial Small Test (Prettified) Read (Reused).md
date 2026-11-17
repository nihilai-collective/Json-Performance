
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 6211.17 | 0.246564 | 63.0614ms | 3808 | 640 | 1330.11 | 584.688 | 0.0534759 | 0.378175 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6208.61 | 0.561598 | 62.4369ms | 3808 | 4890 | 52767.3 | 584.928 | 0.309269 | 0.378292 | 1(Tie) | true |
| simdjson (ondemand) | 3485.89 | 0.206187 | 107.911ms | 3808 | 1280 | 5906.07 | 1041.8 | 0.459545 | 0.690803 | 3(Loss) | true |
| Glaze | 3379.74 | 0.279791 | 112.229ms | 3808 | 4890 | 44198.2 | 1074.52 | 0.657558 | 0.712579 | 4(Loss) | true |
