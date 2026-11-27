
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1741.85 | 0.157662 | 5104.24ms | 83958 | 4890 | 2.56842e+07 | 45967.6 | 0.266796 | 1.7438 | 1(Win) | true |
| simdjson (ondemand) | 1464.5 | 0.274014 | 5927.42ms | 83958 | 320 | 7.18186e+06 | 54672.8 | 0.140234 | 2.07435 | 2(Loss) | true |
