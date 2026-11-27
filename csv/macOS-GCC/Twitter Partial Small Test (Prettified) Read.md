
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 4415.85 | 2.64595 | 86.004ms | 3808 | 320 | 151524 | 822.4 | 0.587084 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4350.25 | 0.687816 | 85.8959ms | 3808 | 4890 | 161220 | 834.801 | 0.0960213 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4207.13 | 2.2789 | 89.0729ms | 3808 | 320 | 123830 | 863.2 | 0.644567 | 1(Tie) | true |
| Jsonifier (two-stage) | 4149.92 | 0.803563 | 91.424ms | 3808 | 2560 | 126589 | 875.1 | 0.0342936 | 4(Loss) | true |
| Glaze | 2935.64 | 0.508489 | 128.667ms | 3808 | 4890 | 193491 | 1237.07 | 1.88367 | 5(Loss) | true |
