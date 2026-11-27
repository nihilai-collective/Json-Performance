
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4569.76 | 1.07763 | 83.604ms | 3808 | 2560 | 187751 | 794.7 | 0.62041 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 4486.71 | 0.774365 | 85.758ms | 3808 | 4890 | 192105 | 809.41 | 0.159094 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4482.36 | 0.713933 | 84.3389ms | 3808 | 4890 | 163607 | 810.196 | 1.2871 | 1(Tie) | true |
| simdjson (reflection) | 4347.8 | 0.694147 | 86.187ms | 3808 | 4890 | 164387 | 835.272 | 2.82802 | 4(Loss) | true |
| Glaze | 3000 | 0.519033 | 128.764ms | 3808 | 4890 | 193041 | 1210.53 | 2.77885 | 5(Loss) | true |
