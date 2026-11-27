
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9585.08 | 0.135322 | 6292.83ms | 631514 | 1280 | 9.25385e+06 | 62833 | 0.132424 | 0.258137 | 1(Win) | true |
| Jsonifier | 9428.9 | 0.0763797 | 6416.14ms | 631514 | 4890 | 1.16388e+07 | 63873.7 | 0.82625 | 0.262453 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 8816.26 | 0.0696686 | 6904.25ms | 631514 | 4890 | 1.10759e+07 | 68312.3 | 0.0715045 | 0.280695 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 8813.09 | 0.423691 | 6955.07ms | 631514 | 30 | 2.51495e+06 | 68336.8 | 0.361257 | 0.280781 | 3(Tie) | true |
| Glaze | 3656.29 | 0.128616 | 8348.61ms | 631514 | 320 | 1.43623e+07 | 164719 | 0.414067 | 0.677019 | 5(Loss) | true |
