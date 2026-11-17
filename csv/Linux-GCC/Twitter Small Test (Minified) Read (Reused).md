
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2386.21 | 0.130545 | 836.156ms | 2821 | 160 | 346.601 | 1127.44 | 0.216109 | 2.23631 | 8.55229 | 1.48706 | 0.000361131 | 6.42503e-05 | 4.43105e-06 | 1(Win) | true |
| simdjson (ondemand) | 2183.18 | 0.0694212 | 845.127ms | 2821 | 1280 | 936.742 | 1232.29 | 0.0254292 | 2.43851 | 9.07267 | 1.44913 | 0.000706753 | 4.34797e-05 | 2.49247e-06 | 2(Loss) | true |
