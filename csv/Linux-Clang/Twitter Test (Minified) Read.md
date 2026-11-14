
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23433.2 | 0.0169271 | 1947.29ms | 466906 | 30 | 310.369 | 19001.9 | 0.34857 | 0.10551 | 1(Win) | true |
| simdjson (stage-1) | 19994.6 | 0.376487 | 2235.24ms | 466906 | 320 | 2.24949e+06 | 22269.8 | 0.422339 | 0.123669 | 2(Loss) | true |
