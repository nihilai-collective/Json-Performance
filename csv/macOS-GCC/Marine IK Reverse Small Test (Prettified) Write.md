
----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8858.52 | 0.269962 | 271.441ms | 24893 | 4890 | 255945 | 2679.89 | 0.164457 | 1(Win) | true |
| Glaze | 3314.53 | 0.361317 | 718.669ms | 24579 | 320 | 208935 | 7072 | 0.0679194 | 2(Loss) | true |
| simdjson (reflection) | 325.371 | 0.129029 | 7453.18ms | 24893 | 320 | 2.83612e+06 | 72962.4 | 0.204618 | 3(Loss) | true |
