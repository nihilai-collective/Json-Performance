
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2224.8 | 0.139956 | 133.796ms | 2889 | 80 | 240.316 | 1238.39 | 0.0695985 | 1.08735 | 1(Win) | true |
| Glaze | 2196.78 | 0.0364421 | 138.218ms | 2889 | 320 | 66.8468 | 1254.18 | 0.131983 | 1.10168 | 2(Loss) | true |
| Jsonifier (two-stage) | 2159.5 | 0.221905 | 136.054ms | 2889 | 4890 | 39195.1 | 1275.83 | 0.18133 | 1.12054 | 3(Loss) | true |
| simdjson (ondemand) | 1008.95 | 0.0496339 | 286.473ms | 2889 | 80 | 146.961 | 2730.72 | 0.096036 | 2.42619 | 4(Loss) | true |
