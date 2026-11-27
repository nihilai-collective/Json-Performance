
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3428.18 | 0.186806 | 859.716ms | 4857 | 1280 | 8154.56 | 1351.15 | 0.0589426 | 1.54548 | 6.70084 | 1.16574 | 0.00145151 | 3.02399e-05 | 1.44765e-05 | 1(Win) | true |
| simdjson (ondemand) | 2282.02 | 0.206601 | 927.36ms | 4857 | 80 | 1406.86 | 2029.78 | 0.0184784 | 2.30365 | 10.1128 | 1.52954 | 0.00251184 | 5.14721e-05 | 3.60305e-05 | 2(Loss) | true |
