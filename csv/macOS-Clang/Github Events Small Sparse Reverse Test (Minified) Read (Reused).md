
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2940.11 | 0.116312 | 58.5119ms | 1691 | 640 | 260.488 | 548.505 | 0.0823939 | 1(Win) | true |
| simdjson (ondemand) | 2049.75 | 0.254918 | 81.695ms | 1691 | 160 | 643.591 | 786.763 | 0.365161 | 2(Loss) | true |
