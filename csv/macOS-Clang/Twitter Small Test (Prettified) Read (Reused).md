
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2182.79 | 0.683873 | 186.399ms | 3770 | 30 | 3806.53 | 1647.13 | 0.671384 | 1(Win) | true |
| simdjson (ondemand) | 2016.01 | 0.207372 | 195.671ms | 3770 | 30 | 410.317 | 1783.4 | 0.00560758 | 2(Loss) | true |
