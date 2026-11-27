
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 738.609 | 0.108037 | 8416.76ms | 2090234 | 160 | 1.36027e+09 | 2.69886e+06 | 0.312996 | 3.35193 | 1(Win) | true |
| simdjson (ondemand) | 654.112 | 0.123415 | 9537.36ms | 2090234 | 40 | 5.65828e+08 | 3.0475e+06 | 0.550631 | 3.78494 | 2(Loss) | true |
