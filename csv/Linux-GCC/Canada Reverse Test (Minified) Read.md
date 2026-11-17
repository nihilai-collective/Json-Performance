
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 674.909 | 0.602946 | 9383.36ms | 2090234 | 40 | 1.26858e+10 | 2.95359e+06 | 1.19773 | 3.66832 | 1(Win) | true |
| simdjson (ondemand) | 634.727 | 0.249887 | 9716.44ms | 2090234 | 30 | 1.84767e+09 | 3.14057e+06 | 0.115694 | 3.90056 | 2(Loss) | true |
