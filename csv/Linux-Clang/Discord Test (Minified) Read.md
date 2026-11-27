
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22706.2 | 0.0659261 | 242.498ms | 56369 | 30 | 73.0851 | 2367.53 | 0.0562857 | 0.107761 | 1(Win) | true |
| simdjson (stage-1) | 19474.9 | 0.0358902 | 280.772ms | 56369 | 40 | 39.259 | 2760.35 | 0.00422634 | 0.125928 | 2(Loss) | true |
