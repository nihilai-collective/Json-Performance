
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4579.37 | 0.174128 | 84.884ms | 3808 | 30 | 57.2057 | 793.033 | 0.172632 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4574.57 | 0.0581717 | 85.2536ms | 3808 | 640 | 136.489 | 793.866 | 0.0141732 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4572.61 | 0.0560475 | 85.477ms | 3808 | 640 | 126.811 | 794.205 | 0.110248 | 1(Tie) | true |
| Glaze | 2692.14 | 0.104982 | 140.796ms | 3808 | 4890 | 9806.95 | 1348.96 | 0.038548 | 4(Loss) | true |
