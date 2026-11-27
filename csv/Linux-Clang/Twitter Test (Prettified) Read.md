
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22024.3 | 0.0680148 | 2769.64ms | 631514 | 2560 | 885540 | 27345.2 | 0.520973 | 0.112301 | 1(Win) | true |
| simdjson (stage-1) | 20642.3 | 0.0822694 | 2928.43ms | 631514 | 2560 | 1.47492e+06 | 29176 | 0.0976043 | 0.119829 | 2(Loss) | true |
