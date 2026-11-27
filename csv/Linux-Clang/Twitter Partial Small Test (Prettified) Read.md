
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8413.28 | 0.199522 | 45.8262ms | 3808 | 40 | 29.6692 | 431.65 | 0.158057 | 0.27697 | 1(Win) | true |
| Jsonifier | 8355.45 | 0.132324 | 45.6867ms | 3808 | 80 | 26.4619 | 434.637 | 0.169394 | 0.278788 | 2(Loss) | true |
| simdjson (ondemand) | 8140.07 | 0.0744439 | 47.9333ms | 3808 | 320 | 35.2976 | 446.137 | 0.357352 | 0.286962 | 3(Loss) | true |
| Glaze | 3935.33 | 0.0514361 | 95.5495ms | 3808 | 160 | 36.0487 | 922.819 | 0.0616698 | 0.611425 | 4(Loss) | true |
