
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 726.193 | 0.549836 | 6038.93ms | 360584 | 160 | 1.08467e+09 | 473538 | 0.150192 | 1(Win) | true |
| simdjson (ondemand) | 242.005 | 0.379264 | 9093.5ms | 360584 | 80 | 2.32346e+09 | 1.42096e+06 | 0.652763 | 2(Loss) | true |
