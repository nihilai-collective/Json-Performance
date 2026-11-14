
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3837.28 | 1.35392 | 76.4298ms | 2889 | 2560 | 241921 | 718 | 0.746475 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 3558.11 | 0.81773 | 83.6641ms | 2889 | 4890 | 196058 | 774.335 | 0.840753 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 3503.52 | 1.12377 | 84.4982ms | 2889 | 2560 | 199932 | 786.4 | 1.00705 | 2(Tie) | true |
| simdjson (reflection) | 3295.43 | 0.678837 | 88.14ms | 2889 | 4890 | 157512 | 836.057 | 1.38508 | 4(Loss) | true |
| Glaze | 2532.32 | 1.46551 | 114.854ms | 2889 | 320 | 81355 | 1088 | 0.147275 | 5(Loss) | true |
