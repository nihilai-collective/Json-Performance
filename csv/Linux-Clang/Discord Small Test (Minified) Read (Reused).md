
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2656.7 | 0.169196 | 197.429ms | 4857 | 4890 | 42553.9 | 1743.51 | 0.036149 | 0.918242 | 1(Win) | true |
| Jsonifier (two-stage) | 2232.44 | 0.0754569 | 231.261ms | 4857 | 80 | 196.095 | 2074.86 | 0.0475709 | 1.09482 | 2(Loss) | true |
| Glaze | 2212.98 | 0.120983 | 231.143ms | 4857 | 40 | 256.503 | 2093.1 | 0.10841 | 1.10538 | 3(Loss) | true |
| simdjson (ondemand) | 908.308 | 0.135867 | 539.263ms | 4857 | 2560 | 122897 | 5099.59 | 0.247103 | 2.71152 | 4(Loss) | true |
